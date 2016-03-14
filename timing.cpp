#include <iomanip>
#include "timing.h"
#include <ctime>

using namespace TIME;

std::ostream& operator<<(std::ostream& f, const Duree & d){ d.afficher(f); return f; }
std::ostream& operator<<(std::ostream& f, const Horaire & h){ h.afficher(f); return f; }


bool Horaire::operator<(const Horaire& h) const{
	if (heure<h.heure) return true;
	if (heure>h.heure) return false;
	if (minute<h.minute) return true;
	if (minute>h.minute) return false;
	return true;
}

QString Horaire::toString() const{
    std::stringstream s;
    s<<std::setfill('0')<<std::setw(2)<<heure<<"H"<<std::setfill('0')<<std::setw(2)<<minute<<std::setfill(' ');
    return QString::fromStdString(s.str());
}

void Horaire::setFromString(QString s){
    QStringList list = s.split("H");
    unsigned short int h = list[0].toInt();
    unsigned short int m = list[1].toInt();
    heure = h;
    minute = m;
}


std::istream& operator>>(std::istream& flot, TIME::Duree& duree){
	unsigned int h,m;
	bool ok=true;
	flot>>h;
	if (flot) while (flot.peek()==' ') flot.ignore(); // passe les espaces
	else ok=false;

	if (!flot) ok=false;

	if(flot.peek()=='H') {
		flot.ignore();
		flot>>m;
		if (!flot) ok=false;
	}
	else {
		ok=false;
	}
	if (ok) duree=Duree(h,m); else flot.clear(std::ios::failbit);
	return flot;
}

bool Duree::operator<(const Duree& d) const{
    return (this->getDureeEnMinutes()<d.getDureeEnMinutes());
}
