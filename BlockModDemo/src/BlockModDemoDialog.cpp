#include "BlockModDemoDialog.h"
#include "ui_BlockModDemoDialog.h"

#include <stdexcept>

#include <QGridLayout>
#include <QFileDialog>

#include <BM_SceneManager.h>
#include <BM_Network.h>

BlockModDemoDialog::BlockModDemoDialog(QWidget *parent) :
	QDialog(parent, Qt::Window | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint),
	ui(new Ui::BlockModDemoDialog),
	m_sceneManager(new BLOCKMOD::SceneManager(this))
{
	ui->setupUi(this);
	ui->gridLayout_2->setColumnStretch(0,1);
	ui->gridLayout_2->setRowStretch(1,1);

	// set scene to network graphics view
	ui->graphicsView->setScene(m_sceneManager);
	ui->graphicsView->setResolution(1); // in pix/m
	ui->graphicsView->setGridStep(80); // 80 pix/m; 8 pix/m for small grid

}


BlockModDemoDialog::~BlockModDemoDialog() {
	delete ui;
}


void BlockModDemoDialog::on_toolButtonNew_clicked() {
	BLOCKMOD::Network n;
	m_sceneManager->setNetwork(n); // network is copied
}


void BlockModDemoDialog::on_toolButtonOpen_clicked() {
	QString fname = QFileDialog::getOpenFileName(this, tr("Select BlockMod file"), QString(), tr("BlockMod files (*.bm)"));
	if (fname.isEmpty())
		return;

	BLOCKMOD::Network n;
	try {
		n.readXML(fname);
		n.checkNames();
		m_sceneManager->setNetwork(n); // network is copied
	} catch (std::runtime_error & e) {
		QString errormsg(e.what());
		ui->plainTextEdit->appendPlainText(errormsg + '\n');
	}
}

void BlockModDemoDialog::on_toolButtonSave_clicked() {
	QString fname = QFileDialog::getSaveFileName(this, tr("Select BlockMod file"), QString(), tr("BlockMod files (*.bm)"));
	if (fname.isEmpty())
		return;
	m_sceneManager->network().writeXML(fname);
}
