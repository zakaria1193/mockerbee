#include "event.h"

// process_event function definition
extern void process_event(Event* event) {
    // Call Event class's process method
    event->process();
}