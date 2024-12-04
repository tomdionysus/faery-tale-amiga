#ifndef FAERY_STATE
#define FAERY_STATE

/* Defines the state of the game */
struct FaeryState {
    struct Process *thistask;     /* This process */
    struct MsgPort *audioport; 
    struct IOAudio *ioaudio;
    BOOL   audio_open;

    UWORD openflags;              /* The open flags */

    struct View *oldview;         /* The original view to be restored on quit */ 
};

/* Macros to clear, set and test open flags */
#define CLRFN()   fstate->openflags = 0
#define SETFN(n)  fstate->openflags |= n
#define TSTFN(n)  fstate->openflags & n

/* Allocation flags for use with the above */
#define AL_BMAP   0x0001
#define AL_GBASE  0x0002
#define AL_HANDLE 0x0004
#define AL_MUSIC  0x0008
#define AL_IMAGE  0x0010
#define AL_SECTOR 0x0020
#define AL_MASK   0x0040
#define AL_SHAPE  0x0080
#define AL_SHADOW 0x0100
#define AL_FONT   0x0200
#define AL_SAMPLE 0x0400
#define AL_PORT   0x0800
#define AL_IOREQ  0x1000
#define AL_TDISK  0x2000
#define AL_TERR   0x4000

#endif
