#include "framework/Router.h"
#include <iostream>
#include <string>
using namespace std;


// -------- Controllers -----------

#include "controller/StaticResourceController.h"
#include "controller/StudentsController.h"
#include "controller/CoursesController.h"
#include "controller/ScoresController.h"

// -------- MyRouter -----------

class MyRouter : public Router
{
public:
	virtual void setupRouting();
	void handleError(const HttpRequest& httpRequest, HttpResponse& httpResponse);
};

void MyRouter::handleError(const HttpRequest& httpRequest, HttpResponse& httpResponse)
{
	ErrorPageController errorPageController;
	errorPageController.handleRequest(httpRequest, httpResponse);
}

void MyRouter::setupRouting()
{
	REGISTER_CTRL_FUN("GET", "/", MainPageController, handleRequest);
	REGISTER_CTRL_FUN("GET", "/public/css/main.css", CssController, handleRequest);
	REGISTER_CTRL_FUN("GET", "/favicon.ico", IconController, handleRequest);
	REGISTER_CTRL_FUN("GET", "/students", StudentsController, handleRequest);
	REGISTER_CTRL_FUN("GET", "/courses", CoursesController, handleRequest);
	REGISTER_CTRL_FUN("GET", "/scorebystudent", ScoresByStudentController, handleRequest);
	REGISTER_CTRL_FUN("GET", "/scorebycourse", ScoresByCourseController, handleRequest);
}

MyRouter myRouter;
