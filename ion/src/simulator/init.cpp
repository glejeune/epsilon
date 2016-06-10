extern "C" {
#include <ion.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include "init.h"
}
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>

#include "display/fltklcd.h"
#include "keyboard/fltkkbd.h"

static FltkLCD * sDisplay;
static FltkKbd * sKeyboard;

#define FRAMEBUFFER_ADDRESS (sDisplay->m_framebuffer)
#define FRAMEBUFFER_BITS_PER_PIXEL 8

void init_platform() {
  Fl::visual(FL_RGB);

  int margin = 10;
  int screen_width = ION_SCREEN_WIDTH;
  int screen_height = ION_SCREEN_HEIGHT;
  int keyboard_height = screen_width;

  Fl_Window * window = new Fl_Window(screen_width+2*margin, margin+screen_height+margin+keyboard_height+margin);

  sDisplay = new FltkLCD(margin, margin, screen_width, screen_height);
  assert(FRAMEBUFFER_BITS_PER_PIXEL == 8);

  sKeyboard = new FltkKbd(margin, margin+screen_height+margin, screen_width, keyboard_height);

  window->end();
  window->show();
}

void ion_set_pixel(uint16_t x, uint16_t y, ion_color_t color) {
  assert(x < ION_SCREEN_WIDTH);
  assert(y < ION_SCREEN_HEIGHT);
  char * byte = (char *)(FRAMEBUFFER_ADDRESS) + ((y*ION_SCREEN_WIDTH)+x);
  *byte = color;
}

void ion_fill_rect(
    uint16_t x, uint16_t y,
    uint16_t width, uint16_t height,
    ion_color_t color)
{
  for (int16_t i = x; i<(x+width); i++) {
    for (int16_t j = y; j<(y+height); j++) {
      ion_set_pixel(i, j, color);
    }
  }
}

bool ion_key_down(ion_key_t key) {
  return sKeyboard->key_down(key);
}

void ion_sleep() {
  usleep(1000);
  sDisplay->redraw();
  Fl::wait();
}
