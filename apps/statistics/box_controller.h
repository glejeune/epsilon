#ifndef STATISTICS_BOX_CONTROLLER_H
#define STATISTICS_BOX_CONTROLLER_H

#include <escher.h>
#include "data.h"

namespace Statistics {

class BoxController : public ViewController, public AlternateEmptyViewDelegate {

public:
  BoxController(Responder * parentResponder, Data * data);
  const char * title() const override;
  View * view() override;
  bool handleEvent(Ion::Events::Event event) override;
  bool isEmpty() override;
  const char * emptyMessage() override;
  Responder * defaultController() override;
private:
  Responder * tabController() const;
  SolidColorView m_view;
  Data * m_data;
};

}


#endif
