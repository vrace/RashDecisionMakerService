#ifndef __SERVICE_CONTROLLER_H__
#define __SERVICE_CONTROLLER_H__

#include "HttpRequest.h"
#include "HttpResponse.h"

#define DECLARE_CONTROLLER(x) HttpResponse x(const HttpRequest &request)

DECLARE_CONTROLLER(BadRequest);
DECLARE_CONTROLLER(WelcomeScreen);
DECLARE_CONTROLLER(RollDice);
DECLARE_CONTROLLER(RandomPick);
DECLARE_CONTROLLER(PairItems);
DECLARE_CONTROLLER(YesOrNo);

#endif
