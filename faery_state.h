#ifndef FAERY_STATE
#define FAERY_STATE

/* Defines the state of the game */
struct FaeryState {
    struct Process *thistask;     /* This process */
    struct MsgPort *audioport; 
    struct IOAudio *ioaudio;
    BOOL      audio_open;

    struct View *oldview;         /* The original view to be restored on quit */ 
};

#endif
