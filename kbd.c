#include <stdio.h>
#include <errno.h>
#include <linux/input.h>
#include <linux/uinput.h>
#include <string.h>
#include <fcntl.h>
#include "termkey.h"
#include "keymap.h"

int fd;
struct uinput_user_dev uidev;
struct input_event ev;
TermKey *tk;

#define check_ret(ret) do{\
  if (ret < 0) {\
    printf("Error at %s:%d\n", __func__, __LINE__);\
    if(tk) termkey_destroy(tk);\
    exit(EXIT_FAILURE);\
  }\
} while(0)

int configure_dev()
{
  int ret, i;
  memset(&uidev, 0, sizeof(uidev));

  fd = open("/dev/uinput", O_WRONLY);
  check_ret(fd);

  snprintf(uidev.name, UINPUT_MAX_NAME_SIZE, "uinput-sample");

  uidev.id.bustype = BUS_USB;
  uidev.id.vendor  = 1;
  uidev.id.product = 1;
  uidev.id.version = 1;

  ret = write(fd, &uidev, sizeof(uidev));
  if (ret != sizeof(uidev)) {
    printf("Failed to write dev structure\n");
    exit(EXIT_FAILURE);
  }

  ret = ioctl(fd, UI_SET_EVBIT, EV_KEY);
  for(i=0;i<sizeof(kmap)/sizeof(*kmap);i++) {
    printf("conf %d\n", kmap[i].kernelcode);
    ret = ioctl(fd, UI_SET_KEYBIT, kmap[i].kernelcode);
    check_ret(ret);
  }
  for(i=0;i<sizeof(keysymmap)/sizeof(*keysymmap);i++){
    printf("conf %d\n", keysymmap[i]);
    ret = ioctl(fd, UI_SET_KEYBIT, keysymmap[i]);
    check_ret(ret);
  }
  for(i=0;i<sizeof(fnmap)/sizeof(*fnmap);i++){
    printf("conf %d\n", fnmap[i]);
    ret = ioctl(fd, UI_SET_KEYBIT, fnmap[i]);
    check_ret(ret);
  }
  ret = ioctl(fd, UI_SET_KEYBIT, KEY_LEFTCTRL);
  check_ret(ret);
  ret = ioctl(fd, UI_SET_KEYBIT, KEY_LEFTALT);
  check_ret(ret);
  ret = ioctl(fd, UI_SET_KEYBIT, KEY_LEFTSHIFT);
  check_ret(ret);

  ret = ioctl(fd, UI_DEV_CREATE);
  check_ret(ret);
}

void send_event(__u16 type, __u16 code, __s32 value)
{
  int ret;
  memset(&ev, 0, sizeof(ev));

  ev.type = type;
  ev.code = code;
  ev.value = value;

  //printf("sending %d %d %d\n", ev.type, ev.code, ev.value);
  ret = write(fd, &ev, sizeof(ev));
  check_ret(ret);
}

void fill_keymap(struct keymap *keymap)
{
  int i;
  for(i=0;i<sizeof(kmap)/sizeof(*kmap);i++) {
    struct map *cur = &kmap[i];
    keymap[cur->usercode].modifier = cur->modifier;
    keymap[cur->usercode].kernelcode = cur->kernelcode;
  }
}

int main(void)
{
  TermKeyResult ret;
  TermKeyKey key;
  char buffer[50];
  struct keymap keymap[500];
  int ctrla = 0;
  TermKeyFormat format = TERMKEY_FORMAT_VIM;

  tk = termkey_new(0, TERMKEY_FLAG_SPACESYMBOL|TERMKEY_FLAG_CTRLC);

  if(!tk) {
    fprintf(stderr, "Cannot allocate termkey instance\n");
    exit(1);
  }

  fill_keymap(keymap);
  configure_dev();
  usleep(50000);

  while((ret = termkey_waitkey(tk, &key)) != TERMKEY_RES_EOF) {
    if(ret == TERMKEY_RES_KEY) {
      termkey_strfkey(tk, buffer, sizeof buffer, &key, format);
      if(key.type == TERMKEY_TYPE_MOUSE) {
        int line, col;
        termkey_interpret_mouse(tk, &key, NULL, NULL, &line, &col);
        printf("%s at line=%d, col=%d\n", buffer, line, col);
      }
      else if(key.type == TERMKEY_TYPE_POSITION) {
        int line, col;
        termkey_interpret_position(tk, &key, &line, &col);
        printf("Cursor position report at line=%d, col=%d\n", line, col);
      }
      else if(key.type == TERMKEY_TYPE_MODEREPORT) {
        int initial, mode, value;
        termkey_interpret_modereport(tk, &key, &initial, &mode, &value);
        printf("Mode report %s mode %d = %d\n", initial ? "DEC" : "ANSI", mode, value);
      }
      else if(key.type == TERMKEY_TYPE_UNKNOWN_CSI) {
        long args[16];
        size_t nargs = 16;
        unsigned long command;
        termkey_interpret_csi(tk, &key, args, &nargs, &command);
        printf("Unrecognised CSI %c %ld;%ld %c%c\n", (char)(command >> 8), args[0], args[1], (char)(command >> 16), (char)command);
      }
      else {
        printf("Key %s\n", buffer);
        printf("type: %d, mod: %d, cn=%d, num=%d\n", key.type, key.modifiers, key.code.codepoint, key.code.number);
        if(ctrla && !(key.modifiers & TERMKEY_KEYMOD_CTRL &&
                (key.code.codepoint == 'A' || key.code.codepoint == 'a'))){
          if(key.code.codepoint == 'q' || key.code.codepoint == 'Q')
            break;
          else {
            ctrla = 0;
            continue;
          }
        }
        if(key.type == TERMKEY_TYPE_UNICODE &&
            key.modifiers & TERMKEY_KEYMOD_CTRL &&
            (key.code.codepoint == 'A' || key.code.codepoint == 'a')) {
          if(ctrla){
            ctrla = 0;
          }else{
            ctrla = 1;
            continue;
          }
        }
        if(key.modifiers & TERMKEY_KEYMOD_CTRL){
          send_event(EV_KEY, KEY_LEFTCTRL, 1);
          send_event( EV_SYN, SYN_REPORT, 0);
        }
        if(key.type == TERMKEY_TYPE_FUNCTION){
          send_event(EV_KEY, fnmap[key.code.codepoint], 1);
          send_event( EV_SYN, SYN_REPORT, 0);
          send_event(EV_KEY, fnmap[key.code.codepoint], 0);
          send_event( EV_SYN, SYN_REPORT, 0);
        } else if (key.type == TERMKEY_TYPE_KEYSYM){
          send_event(EV_KEY, keysymmap[key.code.codepoint], 1);
          send_event( EV_SYN, SYN_REPORT, 0);
          send_event(EV_KEY, keysymmap[key.code.codepoint], 0);
          send_event( EV_SYN, SYN_REPORT, 0);
        } else {
          struct keymap *mp = &keymap[key.code.codepoint];
          if(mp->modifier & SHIFT){
            send_event(EV_KEY, KEY_LEFTSHIFT, 1);
            send_event( EV_SYN, SYN_REPORT, 0);
          }
          send_event(EV_KEY, mp->kernelcode, 1);
          send_event( EV_SYN, SYN_REPORT, 0);
          send_event(EV_KEY, mp->kernelcode, 0);
          send_event( EV_SYN, SYN_REPORT, 0);
          if(mp->modifier & SHIFT){
            send_event(EV_KEY, KEY_LEFTSHIFT, 0);
            send_event( EV_SYN, SYN_REPORT, 0);
          }
        }
        if(key.modifiers & TERMKEY_KEYMOD_CTRL){
          send_event(EV_KEY, KEY_LEFTCTRL, 0);
          send_event( EV_SYN, SYN_REPORT, 0);
        }
      }
    } else if(ret == TERMKEY_RES_ERROR) {
      if(errno != EINTR) {
        perror("termkey_waitkey");
        break;
      }
      printf("Interrupted by signal\n");
    }
  }

  termkey_destroy(tk);
}
