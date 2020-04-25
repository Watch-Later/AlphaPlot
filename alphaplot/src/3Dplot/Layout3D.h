#ifndef LAYOUT3D_H
#define LAYOUT3D_H

#include <QtDataVisualization>

#include "3Dplot/Graph3DCommon.h"
#include "MyWidget.h"

class Matrix;
class Surface3D;
class Bar3D;
class Scatter3D;
class XmlStreamReader;
using namespace QtDataVisualization;

class Layout3D : public MyWidget {
  Q_OBJECT
 public:
  Layout3D(const Graph3DCommon::Plot3DType &plottype, const QString &label,
           QWidget *parent = nullptr, const QString name = QString(),
           Qt::WindowFlags flag = Qt::SubWindow);
  ~Layout3D();
  template <class T>
  T *getGraph3d() {
    switch (plottype_) {
      case Graph3DCommon::Plot3DType::Surface:
        return graph3dsurface_;
      case Graph3DCommon::Plot3DType::Bar:
        return graph3dbars_;
      case Graph3DCommon::Plot3DType::Scatter:
        return graph3dscatter_;
    }
  }

  Surface3D *getSurface3DModifier() const;
  Bar3D *getBar3DModifier() const;
  Scatter3D *getScatter3DModifier() const;

  void exportGraph();
  void saveRastered(const QString &filename, const char *format,
                    const int quality, const int maa, int dpi,
                    const QSize &size);
  void exportGraphwithoutdialog(const QString &name,
                                const QString &selected_filter,
                                const QSize &size);
  void generateSurfacePlot3D(QList<QPair<QPair<double, double>, double>> *data,
                             const Graph3DCommon::Function3DData &funcdata);
  void setMatrixDataModel(Matrix *matrix);

  Matrix *getMatrix() const;
  QSize getContainerSize() const;
  Graph3DCommon::Plot3DType getPlotType() const;
  void load(XmlStreamReader *reader);
  void save(QXmlStreamWriter *writer);

 private:
  Graph3DCommon::Plot3DType plottype_;
  QWidget *main_widget_;
  Q3DSurface *graph3dsurface_;
  Q3DBars *graph3dbars_;
  Q3DScatter *graph3dscatter_;
  Surface3D *surfacemodifier_;
  Bar3D *barmodifier_;
  Scatter3D *scattermodifier_;
  Matrix *matrix_;
};
#endif  // LAYOUT3D_H
