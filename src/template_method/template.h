#include <stdio.h>

typedef struct {
    void (*generateReport)(void*);
    void (*step1)(void*);
    void (*step2)(void*);
    void (*step3)(void*);
} AReportVTable;

typedef struct {
    AReportVTable *vptr;
} AReportGenerator;

static void generateReportAReportGenerator(AReportGenerator *self){
    self->vptr->generateReport(self);
}

static void step1AReportGenerator(AReportGenerator *self){
    self->vptr->step1(self);
}

static void step2AReportGenerator(AReportGenerator *self){
    self->vptr->step2(self);
}

static void step3AReportGenerator(AReportGenerator *self){
    self->vptr->step3(self);
}



// TXT REPORT GENERATOR

typedef struct {
    AReportGenerator base;
} TxtReportGenerator;

static void generateReportTxt(void *self){
    AReportGenerator *aptr = (AReportGenerator*)self;
    step2AReportGenerator(aptr);
    step1AReportGenerator(aptr);
    step3AReportGenerator(aptr);
    printf("TXT REPORT IS READY!\n");
}

static void step1Txt(void *self){
    printf("DOING STEP 1 OF TXT REPORT GENERATION.\n");
}

static void step2Txt(void *self){
    printf("DOING STEP 2 OF TXT REPORT GENERATION.\n");
}

static void step3Txt(void *self){
    printf("DOING STEP 3 OF TXT REPORT GENERATION.\n");
}

static AReportVTable txt_report_vtable = {
    .generateReport = &generateReportTxt,
    .step1 = &step1Txt,
    .step2 = &step2Txt,
    .step3 = &step3Txt,
};

static void initTxtReportGenerator(TxtReportGenerator *generator){
    generator->base.vptr = &txt_report_vtable;
}

// PDF REPORT GENERATOR

typedef struct {
    AReportGenerator base;
} PdfReportGenerator;

static void step0Pdf(void *self);

static void generateReportPdf(void *self){
    AReportGenerator *aptr = (AReportGenerator*)self;
    step0Pdf((PdfReportGenerator*)self);
    step2AReportGenerator(aptr);
    step3AReportGenerator(aptr);
    step1AReportGenerator(aptr);
    printf("PDF WAS REPORTED SUCCESSFULLY!\n");
}

static void step0Pdf(void *self){
    printf("FOUND A PDF FILE STEP 0.\n");
}

static void step1Pdf(void *self){
    printf("REPORTIG A PDF FILE STEP 1.\n");
}

static void step2Pdf(void *self){
    printf("REPORTIG A PDF FILE STEP 2.\n");
}

static void step3Pdf(void *self){
    printf("REPORTIG A PDF FILE STEP 3.\n");
}

static AReportVTable pdf_report_vtable = {
    .generateReport = &generateReportPdf,
    .step1 = &step1Pdf,
    .step2 = &step2Pdf,
    .step3 = &step3Pdf,
};

static void initPdfReportGenerator(PdfReportGenerator *generator){
    generator->base.vptr = &pdf_report_vtable;
}

// WAD REPORT GENERATOR

typedef struct {
    AReportGenerator base;
} WadReportGenerator;

static void step4Wad(void *self);

static void generateReportWad(void *self){
    AReportGenerator *aptr = (AReportGenerator*)self;
    step1AReportGenerator(aptr);
    step2AReportGenerator(aptr);
    step3AReportGenerator(aptr);
    step4Wad((WadReportGenerator*)self);
    printf("WAD REPORT CREATED SUCCESSFULLY!\n");
}

static void step1Wad(void *self){
    printf("STEP 1: PLACING TEXT AS WORLD GEOMETRY...\n");
}

static void step2Wad(void *self){
    printf("STEP 2: PLACING ENTITIES...\n");
}

static void step3Wad(void *self){
    printf("STEP 3: GENERATING BSP TREE...\n");
}

static void step4Wad(void *self){
    printf("STEP 4: OPENING DooM...\n");
}

static AReportVTable wad_report_vtable = {
    .generateReport = &generateReportWad,
    .step1 = &step1Wad,
    .step2 = &step2Wad,
    .step3 = &step3Wad,
};

static void initWadReportGenerator(WadReportGenerator *generator){
    generator->base.vptr = &wad_report_vtable;
}

// flp report generator

typedef struct {
    AReportGenerator base;
} FlpReportGenerator;

static void step5Flp(FlpReportGenerator *self);

static void step4Flp(FlpReportGenerator *self);

static void generateReportFlp(void *self){
    AReportGenerator *aptr = (AReportGenerator*)self;
    step1AReportGenerator(aptr);
    step2AReportGenerator(aptr);
    step3AReportGenerator(aptr);
    step4Flp((FlpReportGenerator*)self);
    step5Flp((FlpReportGenerator*)self);
    printf("FLP REPORT CREATED SUCCESSFULLY!\n");
}

static void step1Flp(void *self){
    printf("1: SETTING UP A WRAPPER...\n");
}

static void step2Flp(void *self){
    printf("2: MAKING A MIDI SEQUENCE...\n");
}

static void step3Flp(void *self){
    printf("3: WAKING UP AND LISTENING TO IT AGAIN...\n");
}

static void step4Flp(FlpReportGenerator *self){
    printf("4: CONFIGURING EQ...\n");
}

static void step5Flp(FlpReportGenerator *self){
    printf("5: PLACING EVENTS...\n");
}

static AReportVTable flp_report_vtable = {
    .generateReport = &generateReportFlp,
    .step1 = &step1Flp,
    .step2 = &step2Flp,
    .step3 = &step3Flp,
};

static void initFlpReportGenerator(FlpReportGenerator *generator){
    generator->base.vptr = &flp_report_vtable;
}
