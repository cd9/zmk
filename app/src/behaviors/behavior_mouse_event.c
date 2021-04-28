#define DT_DRV_COMPAT zmk_behavior_mouse_event

#include <device.h>
#include <drivers/behavior.h>
#include <logging/log.h>

#include <zmk/behavior.h>
#include <zmk/event_manager.h>
#include <zmk/events/keycode_state_changed.h>

LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

static int behavior_mouse_event_init(const struct device *dev) { return 0; };

static int on_keymap_binding_pressed(struct zmk_behavior_binding *binding,
                                     struct zmk_behavior_binding_event event) {
  LOG_DBG("position %d keycode 0x%02X", event.position, binding->param1);
  LOG_DBG("IF THIS APPERAS IN LOGS I WILL CONSIDER IT A SUCCESS");
  return ZMK_EVENT_RAISE(zmk_keycode_state_changed_from_encoded(
      binding->param1, true, event.timestamp));
}

static int on_keymap_binding_released(struct zmk_behavior_binding *binding,
                                      struct zmk_behavior_binding_event event) {
  LOG_DBG("position %d keycode 0x%02X", event.position, binding->param1);
  LOG_DBG("IF THIS APPERAS IN LOGS I WILL CONSIDER IT A SUCCESS");
  return ZMK_EVENT_RAISE(zmk_keycode_state_changed_from_encoded(
      binding->param1, false, event.timestamp));
}

static const struct behavior_driver_api behavior_mouse_event_driver_api = {
    .binding_pressed = on_keymap_binding_pressed,
    .binding_released = on_keymap_binding_released};

#define ME_INST(n)                                                             \
  DEVICE_AND_API_INIT(behavior_mouse_event_##n, DT_INST_LABEL(n),              \
                      behavior_mouse_event_init, NULL, NULL, APPLICATION,      \
                      CONFIG_KERNEL_INIT_PRIORITY_DEFAULT,                     \
                      &behavior_mouse_event_driver_api);

DT_INST_FOREACH_STATUS_OKAY(ME_INST)
