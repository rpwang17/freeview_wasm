#ifndef RENDERVIEW_H
#define RENDERVIEW_H

#include "GenericRenderView.h"

class RenderView : public GenericRenderView
{
  Q_OBJECT
public:
  RenderView(QWidget* parent = NULL);

  void showEvent(QShowEvent* e);
  void mouseReleaseEvent(QMouseEvent *e);

  void MoveCamera(double val);

private:
  int m_nPrevVal;
};

#endif // RENDERVIEW_H
