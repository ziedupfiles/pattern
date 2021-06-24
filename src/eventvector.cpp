#include "include/eventvector.h"

eventElement::eventElement() {
    this->EventType = EventValues::EVENT_DEFAULT;
    this->timeStamp = 0;
    this->confidence = 0;
};
eventElement::eventElement(EventValues typ, float Time, float conf) {
    this->EventType = typ;
    this->timeStamp = Time;
    this->confidence = conf;
};

eventVector::eventVector(int duration){
    this->vectorDuration = duration;
    this->eventSub = this->n.subscribe(this->topic,100, &eventVector::callBack, &(*this));
};

void eventVector::callBack(const vehicle_msgs::BasicInteraction& msg){
    int msgType=0;
    for (int i=0;i<sizeof(this->subTypes);i++ ){
        if ( msg.name == this->subTypes[i] ) {
            msgType=i;
            break;
        }
    }
    int ms = std::chrono::duration_cast< std::chrono::milliseconds >( std::chrono::system_clock::now().time_since_epoch() ).count();
    this->addElement( eventElement(EventValues(msgType),ms,msg.percentage[0]) );
    this->checkTime();
};
void eventVector::addElement(eventElement element){
    this->receivedElements.push_back(element);

}
void eventVector::checkTime(){
    double lastTime = std::chrono::duration_cast< std::chrono::milliseconds >( std::chrono::system_clock::now().time_since_epoch() ).count();
    std::vector<eventElement> temp;
    for (auto it = this->receivedElements.begin();it!=this->receivedElements.end();it++) if ( lastTime - (*it).timeStamp <this->vectorDuration ) temp.push_back(*it);
    this->receivedElements = temp;
}

std::vector<eventElement> eventVector::returnVector(){
    this->checkTime();
    std::vector<eventElement> temp;
    temp= this->receivedElements;
    return temp;
}
