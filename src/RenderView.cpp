#include "RenderView.h"
#include "vtkActor.h"
#include "vtkConeSource.h"
#include "vtkGlyph3D.h"
#include "vtkPolyData.h"
#include "vtkPolyDataMapper.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkRenderer.h"
#include "vtkSmartPointer.h"
#include "vtkSphereSource.h"
#include "vtkCamera.h"
#include <QMessageBox>
#include <QMenu>
#include <QContextMenuEvent>
#include <QAction>
#include <QDebug>

RenderView::RenderView(QWidget* p) : GenericRenderView(p)
{
  vtkNew<vtkConeSource> coneSource;
    coneSource->Update();

    // Create a mapper and actor.
    vtkNew<vtkPolyDataMapper> mapper;
    mapper->SetInputConnection(coneSource->GetOutputPort());

    vtkNew<vtkActor> actor;
    actor->SetMapper(mapper);

    m_renderer->AddActor(actor);
    SetBackgroundColor(QColor(50, 75, 100));
    Render();

    m_nPrevVal = 0;
}

void RenderView::showEvent(QShowEvent *e)
{
//  QMessageBox::information(this, "Shown", "shown");
}

void RenderView::mouseReleaseEvent(QMouseEvent *e)
{
  if (e->button() == Qt::LeftButton)
    GetCamera()->Zoom(1.02);
  GenericRenderView::mouseReleaseEvent(e);
}

void RenderView::MoveCamera(double val)
{
  GetCamera()->Azimuth(val-m_nPrevVal);
  ResetCameraClippingRange();
  m_nPrevVal = val;
  Render();
}
