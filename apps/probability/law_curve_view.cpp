#include "law_curve_view.h"
#include <assert.h>
#include <math.h>

namespace Probability {

LawCurveView::LawCurveView() :
  CurveView(),
  m_law(nullptr),
  m_calculation(nullptr)
{
}

void LawCurveView::setLaw(Law * law) {
  setCurveViewWindow(law);
  m_law = law;
}

void LawCurveView::setCalculation(Calculation * calculation) {
  m_calculation = calculation;
}

void LawCurveView::reload() {
  markRectAsDirty(bounds());
  computeLabels(Axis::Horizontal);
}

void LawCurveView::drawRect(KDContext * ctx, KDRect rect) const {
  float lowerBound = - INFINITY;
  float upperBound = m_calculation->parameterAtIndex(0);
  if (m_calculation->type() == Calculation::Type::RightIntegral) {
    lowerBound = m_calculation->parameterAtIndex(0);
    upperBound = +INFINITY;
  }
  if (m_calculation->type() == Calculation::Type::FiniteIntegral) {
    lowerBound = m_calculation->parameterAtIndex(0);
    upperBound = m_calculation->parameterAtIndex(1);
  }
  ctx->fillRect(bounds(), KDColorWhite);
  drawAxes(ctx, rect, Axis::Horizontal);
  drawLabels(ctx, rect, Axis::Horizontal, false);
  if (m_law->isContinuous()) {
    drawCurve(ctx, rect, m_law, KDColorRed, true, lowerBound, upperBound, true);
  } else {
    drawHistogram(ctx, rect, m_law, 0, 1, false, KDColorBlue, KDColorRed, lowerBound, upperBound+1);
  }
}

char * LawCurveView::label(Axis axis, int index) const {
  assert(axis == Axis::Horizontal);
  return (char *)m_labels[index];
}

float LawCurveView::evaluateModelWithParameter(void * law, float abscissa) const {
  return m_law->evaluateAtAbscissa(abscissa);
}

}