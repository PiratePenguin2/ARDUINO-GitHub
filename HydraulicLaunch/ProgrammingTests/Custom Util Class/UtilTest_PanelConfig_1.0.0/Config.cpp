// Config.cpp

#include Panel.*

/*
 * 
 */

void setup()
{
  Coaster R88Test = new Coaster("Rocket 88 Test");//sim.getCoasterForEntityId(getParentEntityId());
    Panel MainPanel = new Panel("Main Panel");
      mainPanelButtonController = new buttonHelperController();
      mainPanelButtonController.setDelay(250); // Sets how often the buttons should be checked (msec)
      mainPanelButtonController.attachArduinoBoard("Arduino MainPanel", ARDUINO_UNO); // Board name, type of board

      ButtonHelper dispatchA1 = mainPanelButtonController.createButton("Main Dispatch 1");
      ButtonHelper dispatchA2 = mainPanelButtonController.createButton("Main Dispatch 2");
      
      ButtonHelper powerA = mainPanelButtonController.createLatchButton("Main Power");  // includes both latching buttons and 2 way toggle switches

      ButtonHelper eStopA = mainPanelButtonController.createEStopButton("Main E-Stop");



      dispatchA1.attach(10); // NO Pin#. Uses the board attached to the panel the button was declared under
      dispatchA2.attach(11); // NO Pin#
      dispatchA1led.attach(12); // Single Led PWM pin#
      dispatchA2led.attach(13); // Single Led PWM pin#

      powerA.attach(5, 6); // NO Pin#, NC Pin#. Uses the board attached to the panel the button was declared under
      powerAled.attach(7, 8, 9); // Red, Green, and Blue Pin#s

      eStopA.attach(2, 3); // NO Pin#, NC Pin#. Uses the board attached to the panel the button was declared under
      eStopA.attach(4); // Single Led PWM pin#



      
    Panel LaunchPanel = new Panel("Launch Panel");
      launchPanelButtonController = new buttonHelperController();
      launchPanelButtonController.setDelay(250); // Sets how often the buttons should be checked (msec)
      launchPanelButtonController.attachArduinoBoard("Arduino LaunchPanel", ARDUINO_UNO); // Board name, type of board


      ButtonHelper manualLaunchB = launchPanelButtonController.createButton("Manual Launch");
      ButtonHelper aknowledgeB = launchPanelButtonController.createButton("Launch Aknowledge");
      
      ButtonHelper powerB = launchPanelButtonController.createLatchButton("Launch Power");  // includes both latching buttons and 2 way toggle switches

      ButtonHelper eStopB = launchPanelButtonController.createEStopButton("Launch E-Stop");

      manualLaunchB.attach(10); // NO Pin#. Uses the board attached to the panel the button was declared under
      aknowledgeB.attach(11); // NO Pin#
      manualLaunchBled.attach(12); // Single Led PWM pin#
      aknowledgeBled.attach(13); // Single Led PWM pin#

      powerB.attach(5, 6); // NO Pin#, NC Pin#. Uses the board attached to the panel the button was declared under
      powerBled.attach(7, 8, 9); // Red, Green, and Blue Pin#s

      eStopB.attach(2, 3); // NO Pin#, NC Pin#. Uses the board attached to the panel the button was declared under
      eStopB.attach(4); // Single Led PWM pin#

}

void loop() {
  // put your main code here, to run repeatedly:

}
