#include "include/pattern.h"

PatternEvent::PatternEvent() {
    this->EventType = EventValues::EVENT_DEFAULT;
    this->timeDuration = 0;
    this->weight = 0;
    this->sign = 1;
};

PatternEvent::PatternEvent(EventValues typ, float Time, float weight, int sign,std::string linker) {
    this->EventType = typ;
    this->timeDuration = Time;
    this->weight = weight;
    this->sign = sign;
    this->linkPreElement = linker;
};
