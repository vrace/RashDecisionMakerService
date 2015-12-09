#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <time.h>
#include <fstream>

#include "ServiceController.h"

extern "C"
{
#include "mongoose/mongoose.h"
}

#define INVOKE_CONTROLLER(x) x(request).Send(conn)

void RequestDispatch(mg_connection *conn, int ev, void *evdata)
{
	if (ev == MG_EV_HTTP_REQUEST)
	{
		http_message *msg = static_cast<http_message*>(evdata);
		HttpRequest request(*msg);

		const std::string &uri = request.uri();
		HttpRequestMethod method = request.method();

		std::cout << "[" << request.rawMethod() << "] " << request.uri() << std::endl;

		if (method == requestMethodGET && (uri == "/" || uri == "/help"))
		{
			INVOKE_CONTROLLER(WelcomeScreen);
		}
		else if (method == requestMethodGET && (uri == "/d" || uri.find("/d/") == 0))
		{
			INVOKE_CONTROLLER(RollDice);
		}
		else if (method == requestMethodGET && (uri.find("/pick/") == 0))
		{
			INVOKE_CONTROLLER(RandomPick);
		}
		else if (method == requestMethodGET && (uri.find("/pair/") == 0))
		{
			INVOKE_CONTROLLER(PairItems);
		}
		else if (method == requestMethodGET && (uri == "/yesno" || uri.find("/yesno/") == 0))
		{
			INVOKE_CONTROLLER(YesOrNo);
		}
		else
		{
			INVOKE_CONTROLLER(BadRequest);
		}
	}
}

int main(void)
{
	mg_mgr mgr;
	mg_connection *conn;

	srand(time(0));

	mg_mgr_init(&mgr, nullptr);
	conn = mg_bind(&mgr, "8000", RequestDispatch);
	mg_set_protocol_http_websocket(conn);

	std::cout << "Rash Decision Maker RESTful Service started" << std::endl;

	for (;;)
	{
		mg_mgr_poll(&mgr, 3000);
	}

	mg_mgr_free(&mgr);

	return 0;
}
