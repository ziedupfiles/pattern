#include "include/basicinteraction.h"
#include "include/patternmatcher.h"
#include "std_msgs/String.h"
#include "include/newpattern.h"

#include <vector>

int main (int argc, char** argv)
{
   ros::init(argc, argv,"receiver");
   eventVector* receiver = new eventVector(5000);
   newSubPattern sub1 = newSubPattern();
   sub1.addElement(newPatternEvent(EventValues::handsOff,0,0,80.0/100,1) );
   sub1.addElement(newPatternEvent(EventValues::handsOff,8,20,60.0/100,-1) );
   newSubPattern sub2 = newSubPattern();
   sub2.addElement(newPatternEvent(EventValues::handsOn,20,27,79.0/100,1) );
   sub2.addElement( newPatternEvent(EventValues::sittingMid,20,100,50.0/100,1) );
   std::vector<newSubPattern> subPatterns = {sub1,sub2};

    newPattern* pattern = new newPattern(subPatterns);
    pattern->vect = receiver;
    ros::Rate loop_rate(10);

     while (ros::ok()){
        receiver->spin();
        std::list<long int> returnlist = pattern->patternIsValid();
        std::cout<<"\npattern valid at"<<std::endl;
        for ( auto it =returnlist.begin(); it!=returnlist.end();it++ ) std::cout<<*it<<std::endl;
        std::cout<<receiver->receivedElements.size()<<std::endl;
        loop_rate.sleep();
     }

   /*PatternMatcher* matcher = new PatternMatcher(4000);
   std::vector<PatternEvent> sittingPatternElements;

   sittingPatternElements.push_back( PatternEvent( EventValues::handsOff  , 100, 0.2 ,1,"-1" ) );
   sittingPatternElements.push_back( PatternEvent( EventValues::handsOn  , 300, 0.6 ,1,"sequence" ) );
   sittingPatternElements.push_back( PatternEvent( EventValues::leaningBack  , 200, 0.1 , -1,"sequence" ) );
   sittingPatternElements.push_back( PatternEvent( EventValues::sittingMid  , 200, 0.2 , 1,"or" ) );

   std::vector<PatternEvent> patr = {  };
   Pattern* takingPattern = new Pattern ( sittingPatternElements );
   matcher->addPattern(takingPattern);

   ros::Rate loop_rate(10);

   //eventVector* vec = new eventVector(5000);vec->spin();
   while (ros::ok()){

      matcher->spin();
       PatternsFound p = matcher->CalculatePatternWeights( *takingPattern );
       for ( auto it =p.totalWeightList.begin(); it!=p.totalWeightList.end();it++ ) std::cout<<*it<<std::endl;
       loop_rate.sleep();

   }*/


}
