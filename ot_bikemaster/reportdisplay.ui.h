/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you want to add, delete, or rename functions or slots, use
** Qt Designer to update this file, preserving your code.
**
** You should not define a constructor or destructor in this file.
** Instead, write your code in functions called init() and destroy().
** These will automatically be called by the form's constructor and
** destructor.
*****************************************************************************/


using namespace std;
void ReportDisplay::init(){
    this->setWFlags (Qt::WDestructiveClose);
}

void ReportDisplay::writeReport( QString & report , QString& name)
{
    this->ReportText->setText(report);
    this->suggestName = name;
}


void ReportDisplay::saveReportSlot()
{
    QString baas = QFileDialog::getSaveFileName(suggestName,"AnyFile",this,"Save file dialog.", "Save your report.");
    baas.append(".bm2k");
    QFile reportFile(baas);
    if ( !reportFile.open( IO_WriteOnly ) ) {
        cerr << "FAIL TO OPEN FILE FOR WRITING" << endl;
        return;
    } 
    QTextStream ts( &reportFile );
    ts << this->ReportText->text();
    reportFile.close();
    this->close();
}
