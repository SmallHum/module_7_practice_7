#include "template.h"
#include <stdlib.h>

static void doTemplateMethodClientCode(){
    AReportGenerator *txt_report = (AReportGenerator*)malloc(sizeof(TxtReportGenerator));
    initTxtReportGenerator((TxtReportGenerator*)txt_report);

    generateReportAReportGenerator(txt_report);

    AReportGenerator *pdf_report = (AReportGenerator*)malloc(sizeof(PdfReportGenerator));
    initPdfReportGenerator((PdfReportGenerator*)pdf_report);

    generateReportAReportGenerator(pdf_report);

    AReportGenerator *wad_report = (AReportGenerator*)malloc(sizeof(WadReportGenerator));
    initWadReportGenerator((WadReportGenerator*)wad_report);

    generateReportAReportGenerator(wad_report);

    AReportGenerator *flp_report = (AReportGenerator*)malloc(sizeof(FlpReportGenerator));
    initFlpReportGenerator((FlpReportGenerator*)flp_report);

    generateReportAReportGenerator(flp_report);

    free(txt_report);
    free(pdf_report);
    free(wad_report);
    free(flp_report);
}
