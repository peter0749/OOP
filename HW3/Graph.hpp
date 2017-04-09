#ifndef GRAPH_HPP
#define GRAPH_HPP

class Line {
    private:
        double x0,y0,x1,y1;
        static const double _eps;
    public:
        // constructor
        Line(double x0=0.0, double y0=0.0, double x1=1.0, double y1=0.0) {
            this->x0 = x0;
            this->x1 = x1;
            this->y0 = y0;
            this->y1 = y1;
        }

        // member functions

        inline double get_x0(void) const { return this->x0; }
        inline double get_x1(void) const { return this->x1; }
        inline double get_y0(void) const { return this->y0; }
        inline double get_y1(void) const { return this->y1; }

        double slope (void) {
            double dx = x1 - x0;
            double dy = y1 - y0;
            if(std::abs(dx) < this->_eps) 
                throw std::runtime_error("Warning: Divde by zero in slope method. The slope is undefined...");
            return dy / dx;
        }

        double y_intercept(void) {
            // not implement yet
            double res(0.0);
            try {
                res = this->y0 - this->slope() * this->x0;
            } catch (std::runtime_error err) {
#ifndef Release
                std::cerr << err.what() << std::endl;
#endif
                res = this->y0;
            }
            return res;
        }

        void vshift(double step=0.0) {
            this->y0 += step;
            this->y1 += step;
        }
};

const double Line::_eps = 1e-7;

class Line2 {
    private:
        double x, y, dx, dy;
        static const double _eps;
    public:

        inline double get_x(void) const { return this->x; }
        inline double get_dx(void) const { return this->dx; }
        inline double get_y(void) const { return this->y; }
        inline double get_dy(void) const { return this->dy; }

        Line2 (double x=0.0, double y=0.0, double dx=1.0, double dy=1.0) {
            this->x = x;
            this->y = y;
            this->dx = dx;
            this->dy = dy;
        }

        bool normal (Line2 &ext) {
            ext.dx = -this->dy;
            ext.dy = this->dx;
            ext.x = this->x;
            ext.y = this->y;

            if (std::abs(this->dx)<Line2::_eps && std::abs(this->dy)<Line2::_eps) {
#ifndef Release
                std::cerr << "There are no normal line of zero vectors!" << std::endl;
#endif
                return false; // fails
            }
            return true;
        }
};
const double Line2::_eps = 1e-7;

class Circle {
    protected:
        double cx, cy, radius;
        static const double _eps;
    public:
        Circle(double x=0.0, double y=0.0, double r=1.0 ) {
            this->cx = x;
            this->cy = y;
            this->radius = r;
        }

        inline double get_x(void) const { return this->cx; }
        inline double get_y(void) const { return this->cy; }
        inline double get_radius(void) const { return this->radius; }

        inline void set_center(const double x, const double y) {
            this->cx = x;
            this->cy = y;
        }
        inline void set_radius(const double r) {
            this->radius = r;
        }
        inline bool is_inside(const double x, const double y) {
            double dx = x - this->cx;
            double dy = y - this->cy;
            return dx*dx + dy*dy <= this->radius*this->radius;
        }
};
const double Circle::_eps = 1e-7;

class Circle2:public Circle {
    private:
        double x0,y0,x1,y1;
    public:
        Circle2(double x0=-1.0, double y0=0.0, double x1=1.0, double y1=0.0) {
            this->cx = ( x0 + x1 ) / 2.0l;
            this->cy = ( y0 + y1 ) / 2.0l;
            x0 = (x1-x0);
            y0 = (y1-y0);
            this->radius = sqrtl(x0*x0+y0*y0) / 2.0l;
        }
        // The rest is same as class Circle
};

std::ostream &operator << (std::ostream &os, const Line &l) {
    os << "(" << l.get_x0() << ", " << l.get_y0() << ")";
    os << "(" << l.get_x1() << ", " << l.get_y1() << ")";
    return os;
}
std::istream &operator >> (std::istream &is, Line &l) {
    double a, b, c, d;
    is >> a >> b >> c >> d;
    l = Line(a, b, c, d);
    return is;
}
std::ostream &operator << (std::ostream &os, const Line2 &l) {
    os << "(" << l.get_x() << ", " << l.get_y() << ")";
    os << "(" << l.get_dx() << ", " << l.get_dy() << ")";
    return os;
}
std::istream &operator >> (std::istream &is, Line2 &l) {
    double a, b, c, d;
    is >> a >> b >> c >> d;
    l = Line2(a, b, c, d);
    return is;
}
std::ostream &operator << (std::ostream &os, const Circle &l) {
    os << "(" << l.get_x() << ", " << l.get_y() << ")";
    os << "(" << l.get_radius() << ")";
    return os;
}
std::istream &operator >> (std::istream &is, Circle &l) {
    double x, y, r;
    is >> x >> y >> r;
    l = Circle(x, y, r);
    return is;
}
std::istream &operator >> (std::istream &is, Circle2 &l) {
    double x0, y0, x1, y1;
    is >> x0 >> y0 >> x1 >> y1;
    l = Circle2(x0, y0, x1, y1);
    return is;
}
#endif
