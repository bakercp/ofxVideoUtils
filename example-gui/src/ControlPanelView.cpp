//
//  ControlPanelView.cpp
//  example-gui
//
//  Created by Jason Van Cleave on 10/15/13.
//
//

#include "ControlPanelView.h"

ControlPanelView::ControlPanelView()
{

}
void ControlPanelView::setup(ofApp* app)
{
    this->app = app;
    parameters.add(app->isRecording);
    parameters.add(app->bufferPosition);
    app->bufferPosition.addListener(this, &ControlPanelView::onBufferPositionChanged);
    app->isRecording.addListener(this, &ControlPanelView::onIsRecordingChanged);
    gui.setup(parameters);
}

void ControlPanelView::onBufferPositionChanged(ofVec3f & point)
{
    ofLogVerbose() << "onBufferPositionChanged";
}
void ControlPanelView::onIsRecordingChanged(bool & doRecording)
{
    ofLogVerbose() << "onIsRecordingChanged";
    if (doRecording)
    {
        app->startRecording();
    }
}

void ControlPanelView::update()
{

}

void ControlPanelView::draw()
{
    gui.draw();
}