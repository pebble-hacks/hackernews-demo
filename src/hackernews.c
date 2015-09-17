#include <pebble.h>

static Window *s_window;
static TextLayer *s_text_layer;
static char *s_text;

void init(void) {
  s_window = window_create();
  s_text_layer = text_layer_create(layer_get_bounds(window_get_root_layer(s_window)));
  s_text = malloc(sizeof("data"));
  strncpy(s_text, "data", sizeof("data"));

  text_layer_set_text(s_text_layer, s_text);
  text_layer_set_text_alignment(s_text_layer, GTextAlignmentCenter);
  layer_add_child(window_get_root_layer(s_window), text_layer_get_layer(s_text_layer));

  window_stack_push(s_window, true);
}

void deinit(void) {
  free(s_text);
  text_layer_destroy(s_text_layer);
  window_destroy(s_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
