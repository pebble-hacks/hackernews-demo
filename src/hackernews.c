#include <pebble.h>

static Window *s_window;
static TextLayer *s_text_layer;
static char *s_text;

enum APP_MESSAGE_KEYS {
  GREETING = 0,
};

void send_message(char *message) {
  DictionaryIterator *iter;

  app_message_outbox_begin(&iter);
  dict_write_cstring(iter, GREETING, message);

  dict_write_end(iter);
  app_message_outbox_send();
}

void in_dropped_handler(AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Incoming message dropped: %d", reason);
}

void in_received_handler(DictionaryIterator *received, void *context) {
  // We're going to do something here
}

void out_failed_handler(DictionaryIterator *failed, AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Outgoing message failed: %d", reason);
}

void out_sent_handler(DictionaryIterator *sent, void *context) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Message sent successfully");
}

void app_message_init(void) {
  app_message_register_inbox_dropped(in_dropped_handler);
  app_message_register_inbox_received(in_received_handler);
  app_message_register_outbox_failed(out_failed_handler);
  app_message_register_outbox_sent(out_sent_handler);

  app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());

  send_message("hello");
}

void app_message_deinit(void) {
  app_message_deregister_callbacks();
}

void init(void) {
  app_message_init();

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
  app_message_deinit();

  free(s_text);
  text_layer_destroy(s_text_layer);
  window_destroy(s_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
