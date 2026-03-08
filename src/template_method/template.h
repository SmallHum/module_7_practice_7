#include <stdio.h>

typedef struct {
    void (*step1)(void*);
    void (*step2)(void*);
    void (*step3)(void*);
    void (*step4)(void*);
    void (*finish)(void*);
} AReportVTable;

static void doNothing(void *self){
}

typedef struct {
    AReportVTable *vptr;
} AReportGenerator;

static void step1AReportGenerator(AReportGenerator *self){
    self->vptr->step1(self);
}

static void step2AReportGenerator(AReportGenerator *self){
    self->vptr->step2(self);
}

static void step3AReportGenerator(AReportGenerator *self){
    self->vptr->step3(self);
}

static void step4AReportGenerator(AReportGenerator *self){
    self->vptr->step4(self);
}

static void finishAReportGenerator(AReportGenerator *self){
    self->vptr->finish(self);
}

//////////////////////////////////////////////////////////////////////////////////
// since this method isn't going to be overriden, i'm not going to include it in the vtable
//////////////////////////////////////////////////////////////////////////////////

static void generateReportAReportGenerator(AReportGenerator *self){
    step1AReportGenerator(self);
    step2AReportGenerator(self);
    step3AReportGenerator(self);
    step4AReportGenerator(self);
    finishAReportGenerator(self);
}

// TXT REPORT GENERATOR

typedef struct {
    AReportGenerator base;
} TxtReportGenerator;

static void step1Txt(void *self){
    printf("1: WRITING TEXT INTO A TXT...\n");
}

static void finishTxt(void *self){
    printf("TXT SAVED!\n");
}

static AReportVTable txt_report_vtable = {
    .step1 = &step1Txt,
    .step2 = &doNothing,
    .step3 = &doNothing,
    .step4 = &doNothing,
    .finish = &finishTxt
};

static void initTxtReportGenerator(TxtReportGenerator *generator){
    generator->base.vptr = &txt_report_vtable;
}

// PDF REPORT GENERATOR

typedef struct {
    AReportGenerator base;
} PdfReportGenerator;

static void step1Pdf(void *self){
    printf("1: FOUND A PDF TO REPORT...\n");
}

static void step2Pdf(void *self){
    printf("2: CHECKING THEIR INTERNET ACTIVITY...\n");
}

static void step3Pdf(void *self){
    printf("3: GROOMING DETECTED.\n");
}

static void finishPdf(void *self){
    printf("PDF REPORTED!\n");
}

static AReportVTable pdf_report_vtable = {
    .step1 = &step1Pdf,
    .step2 = &step2Pdf,
    .step3 = &step3Pdf,
    .step4 = &doNothing,
    .finish = &finishPdf
};

static void initPdfReportGenerator(PdfReportGenerator *generator){
    generator->base.vptr = &pdf_report_vtable;
}

// WAD REPORT GENERATOR

typedef struct {
    AReportGenerator base;
} WadReportGenerator;

static void step1Wad(void *self){
    printf("1: PLACING TEXT AS WORLD GEOMETRY...\n");
}

static void step2Wad(void *self){
    printf("2: GENERATING A BSP TREE...\n");
}

static void finishWad(void *self){
    printf("OPENING DOOM...\n");
}

static AReportVTable wad_report_vtable = {
    .step1 = &step1Wad,
    .step2 = &step2Wad,
    .step3 = &doNothing,
    .step4 = &doNothing,
    .finish = &finishWad
};

static void initWadReportGenerator(WadReportGenerator *generator){
    generator->base.vptr = &wad_report_vtable;
}

// FLP REPORT GENERATOR

typedef struct {
    AReportGenerator base;
} FlpReportGenerator;

static void step1Flp(void *self){
    printf("1: FIGURING OUT HOW THE FORMAT WORKS...\n");
}

static void step2Flp(void *self){
    printf("2: MAKING A MIDI SEQUENCE...\n");
}

static void step3Flp(void *self){
    printf("3: ADDING EQ AND REVERB...\n");
}

static void step4Flp(void *self){
    printf("4: PLACING EVENTS INTO THE FILE...\n");
}

static void finishFlp(void *self){
    printf("FLP REPORT FINISHED.\n");
}

static AReportVTable flp_report_vtable = {
    .step1 = &step1Flp,
    .step2 = &step2Flp,
    .step3 = &step3Flp,
    .step4 = &step4Flp,
    .finish = &finishFlp
};

static void initFlpReportGenerator(FlpReportGenerator *generator){
    generator->base.vptr = &flp_report_vtable;
}
