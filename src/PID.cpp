#include "PID.h"
#include <math.h>

/*
* TODO: Complete the PID class.
*/

PID::PID() {
	Kp = 1.0;
	Kd = 1.0;
	Ki = 1.0;
	p_error = 0.0;
	d_error = 0.0;
	i_error = 0.0;
	prev_cte = 0.0;
	first_run = true;
#ifdef _DEBUG
	logfile = std::ofstream("PID_Controller.log");
#endif
}

PID::~PID() {
#ifdef _DEBUG
	logfile.close();
#endif
}

void PID::Init(double Kp, double Ki, double Kd) {
	this->Kp = Kp;
	this->Kd = Kd;
	this->Ki = Ki;
#ifdef _DEBUG
	logfile << "Kp: " << Kp << " Ki: " << Ki << " Kd: " << Kd << std::endl;
#endif
}

void PID::UpdateError(double cte) {
	p_error = cte;
	if (first_run) {
		d_error = 0.0;
		first_run = false;
	} else {
		d_error = cte - prev_cte;
	}
	i_error += cte;
#ifdef _DEBUG
	logfile << cte << "\t" << p_error << "\t" << d_error << "\t" << i_error << "\t" << prev_cte << std::endl;
#endif
	prev_cte = cte;
}

double PID::TotalError() {
	double t_err = -1.0 * ((Kp * p_error) + (Kd * d_error) + (Ki * i_error));
#ifdef _DEBUG
	logfile << "Total Error: " << t_err << std::endl;
	logfile << "Calculation:\n";
	logfile << "Kp: " << Kp << " p_error: " << p_error << "\n";
	logfile << "Ki: " << Ki << " i_error: " << i_error << "\n";
	logfile << "Kd: " << Kd << " d_error: " << d_error << "\n";
#endif
	return t_err;
}

