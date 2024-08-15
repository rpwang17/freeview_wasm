#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QFileDialog>
#include "vtkCamera.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  connect(ui->actionOpen_File, SIGNAL(triggered(bool)), SLOT(OnFileOpen()));

  QTreeWidgetItem* v_item = new QTreeWidgetItem;
  v_item->setText(0, "Volumes");
  ui->treeWidget->addTopLevelItem(v_item);
  QTreeWidgetItem* item = new QTreeWidgetItem(v_item);
  item->setText(0, "Volume 1");
  v_item->setExpanded(true);

  connect(ui->sliderAngle, SIGNAL(valueChanged(int)), SLOT(OnSliderAngle(int)), Qt::QueuedConnection);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::OnFileOpen()
{
  QFileDialog::getOpenFileContent(tr("Image Files (*.mgz *.nii)"), [](const QString &fileName, const QByteArray &data){});
}

void MainWindow::OnSliderAngle(int n)
{
  ui->widgetView->MoveCamera(n);
  ui->widgetView2->MoveCamera(n);
  ui->widgetView3->MoveCamera(n);
  ui->widgetView4->MoveCamera(n);
}
