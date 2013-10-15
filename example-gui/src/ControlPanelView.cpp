//
//  ControlPanelView.cpp
//  example-gui
//
//  Created by Jason Van Cleave on 10/15/13.
//
//

#include "ControlPanelView.h"


void ControlPanelView::setup()
{
    //this->app = app;
    //isRecording.set("isRecording", app->isRecording);
    
    parameters.add(isRecording);
    isRecording.addListener(this, &ControlPanelView::onIsRecordingChanged);
}


void ControlPanelView::onIsRecordingChanged(bool & doRecording)
{
    if (doRecording)
    {
        //app->startRecording();
    }
}

void ControlPanelView::update()
{

}

void ControlPanelView::draw()
{

}