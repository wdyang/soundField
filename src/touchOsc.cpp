#include "touchOsc.h"


void testApp::parseIpadOSCMessage(){
    ofxOscMessage m;
    ipadReceiver.getNextMessage(&m);
    
    if(!bSenderLive){
        ipadIP = m.getRemoteIp();
        ipadSender.setup(ipadIP, PORT_TO_IPAD);
    }
    
    string msg_string="";
    string raw_address;
    
    raw_address = m.getAddress();
    cout<<raw_address<<endl;

    if(raw_address=="/1/connect"){
        int val = m.getArgAsInt32(0);
        cout<<"connect request received: "<<val<<endl;
        if(val==0){
            oscSendInitConfig();
        }
    }else if(raw_address.find("fader")<10){ //string.find doesn't return -1 when there is no match
        int channel = (int) raw_address[8] - '0';
        cout<<"channel "<<raw_address[8]<<" "<<channel<<"string find is "<<raw_address.find("fader")<<endl;
        float val = m.getArgAsFloat(0);
        volume[channel]=val;
    }else if(raw_address=="/1/rotate"){
        float delta = 0.02;
        int val = m.getArgAsInt32(0);
        if(val >0){
            rotate+=delta;
            if(rotate>=8) rotate = 0;
        }else{
            rotate-=delta;
            if(rotate<0) rotate = 8;
        }
        cout<<"rotate "<<rotate<<endl;
    }else{
        cout<<"not handled: "<<raw_address<<endl;
    }

    
    //    else if(raw_address == "/1/fader0"){
//        float val = m.getArgAsFloat(0);
//        volume[0]=val;
//    }else if(raw_address == "/1/fader1"){
//        float val = m.getArgAsFloat(0);
//        volume[1]=val;
//    }else if(raw_address == "/1/fader2"){
//        float val = m.getArgAsFloat(0);
//        volume[2]=val;
//    }else if(raw_address == "/1/fader3"){
//        float val = m.getArgAsFloat(0);
//        volume[3]=val;
//    }else if(raw_address == "/1/fader4"){
//        float val = m.getArgAsFloat(0);
//        volume[4]=val;
//    }else if(raw_address == "/1/fader5"){
//        float val = m.getArgAsFloat(0);
//        volume[5]=val;
//    }else if(raw_address == "/1/fader6"){
//        float val = m.getArgAsFloat(0);
//        volume[6]=val;
//    }else if(raw_address == "/1/fader7"){
//        float val = m.getArgAsFloat(0);
//        volume[7]=val;
//    };
//    else if(raw_address=="/1/fader"){
//        int val = m.getArgAsInt32(0);
//        if(val==0) ofToggleFullscreen();
//    }else if(raw_address=="/1/drawFluid"){
////        drawFluid = m.getArgAsInt32(0);
//    }else if(raw_address.find("/1/drawMode/1/")!=string::npos){  //   "/1/drawMode/1/1"
//
//        char id_ch = raw_address[raw_address.length()-1];
//        int id = id_ch - '0';
//        switch (id) {
//            case 1:
////                fluidDrawer.setDrawMode(msa::fluid::kDrawColor);
//                break;
//            case 2:
////                fluidDrawer.setDrawMode(msa::fluid::kDrawMotion);
//                break;
//            case 3:
////                fluidDrawer.setDrawMode(msa::fluid::kDrawSpeed);
//                break;
//            case 4:
////                fluidDrawer.setDrawMode(msa::fluid::kDrawVectors);
//                break;
//            default:
//                break;
//        }
//        oscSendInt("/1/drawMode/1/1", 0);
//        oscSendInt("/1/drawMode/1/2", 0);
//        oscSendInt("/1/drawMode/1/3", 0);
//        oscSendInt("/1/drawMode/1/4", 0);
//        oscSendInt(raw_address, true);
//    }else if(raw_address=="/1/doRGB"){
////        fluidSolver.doRGB = m.getArgAsInt32(0);
//    }
//    }else{
//        cout<<"not handled: "<<raw_address<<endl;
//    }

}

void testApp::oscSendInitConfig(){
    oscSendString("/1/connect/color", "green");
    for(int i=0; i<8; i++){
        char address[24];
        sprintf(address, "/1/fader%i", i);
        oscSendFloat(address, volume[i]);
    };
//    oscSendInt("/1/drawFluid", drawFluid);
//    oscSendInt("/1/drawMode/1/1", (fluidDrawer.getDrawMode() == msa::fluid::kDrawColor));
//    oscSendFloat("/1/viscocity", fluidSolver.viscocity);
//    oscSendFormatedFloat("/1/labelViscocity", fluidSolver.viscocity, 5);
//    
//    oscSendFloat("/1/musicVolume", music.getVolume());
//    oscSendFloat("/1/labelVolume", music.getVolume());
//    
//    oscSendInt("/1/bTuioOn", bTuioOn);
//    
//    for(int i=0; i<NumPreset; i++){
//        char address[24];
//        sprintf(address, "/1/labelPreset%i", i+1);
//        oscSendString(address, presetName[i]);
//    }
//    oscSendInt("/1/savePreset/visible", false);
//    oscSendString("/1/labelSaveState", "Show Save");
    
}

void testApp::oscSendString(const string &address, const string &msg){
    ofxOscMessage m;
    m.setAddress(address);
    m.addStringArg(msg);
    ipadSender.sendMessage(m);
}

void testApp::oscSendFloat(const string &address, float msg){
    ofxOscMessage m;
    m.setAddress(address);
    m.addFloatArg(msg);
    ipadSender.sendMessage(m);
}

void testApp::oscSendFormatedFloat(const string &address, float msg, int precision){
    char st[24], formatst[20];
    sprintf(formatst, "%%.%df", precision);
    sprintf(st, formatst, msg);
    cout<<formatst<<" "<<st<<endl;
    ofxOscMessage m;
    m.setAddress(address);
    m.addStringArg(st);
    ipadSender.sendMessage(m);
}


void testApp::oscSendInt(const string &address, int msg){
    ofxOscMessage m;
    m.setAddress(address);
    m.addIntArg(msg);
    ipadSender.sendMessage(m);
}

//void testApp::saveToXml(int i){
//    string fname = presetName[i]+".xml";
//    gui.setAutoSave(false);
//    gui.currentPage().setXMLName(fname);
//    gui.saveToXML();
//    gui.currentPage().setXMLName(defaultPresetName);
//    gui.setAutoSave(true);
//}
//
//void testApp::loadFromXml(int i){
//    string fname = presetName[i]+".xml";
//    gui.setAutoSave(false);
//    gui.currentPage().setXMLName(fname);
//    gui.loadFromXML();
//    gui.currentPage().setXMLName(defaultPresetName);
//    gui.setAutoSave(true);
//}
//
//
//string testApp::msToTime(int ms){
//    
//    int sec = ms/1000;
//    std::ostringstream s;
//    s<<sec/60<<":"<<sec%60;
//    
//    return s.str();
//}
