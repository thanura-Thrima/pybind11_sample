#include <iostream>
#include <cstring>

#include <pybind11/embed.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>
#include <pybind11/stl_bind.h>

#include <opencv2/opencv.hpp>

namespace py = pybind11;
using namespace py::literals;

    
class App{
    public:
    static std::shared_ptr<App> getApplication(){
        if(s_App == nullptr)
        {
            s_App = std::make_shared<App>();
        }
        return s_App;
    }

    void setImage(cv::Mat& image)
    {
        m_image = image;
    }

    public:
    static std::shared_ptr<App> s_App;
    std::string m_appName{"my Application"};
    cv::Mat m_image;
};
std::shared_ptr<App> App::s_App = nullptr;

class ApplicationInterface{
    public:
    ApplicationInterface() {
        m_app = App::getApplication();
        size =m_app->m_image.rows*m_app->m_image.cols*m_app->m_image.channels();
        m_arr.resize(size);
    }
    void get(){ std::cout<<"get function : "<< m_app->m_appName<<std::endl; }
    std::vector<uchar> getImage()
    { 
        std::memcpy(m_arr.data(), m_app->m_image.data, size);
        return m_arr;
    }
    private:
    std::shared_ptr<App> m_app;
    public:
    std::vector<uchar> m_arr;
    size_t size{0}; 
};

// this is to transfer stl containers fast, otherwise it needs two mem copies
PYBIND11_MAKE_OPAQUE(std::vector<uchar>);

PYBIND11_EMBEDDED_MODULE(ApplicationLogic, m) {
    // `m` is a `py::module_` which is used to bind functions and classes

    py::class_<std::vector<uchar>>(m, "IntVector")
    .def(py::init<>())
    .def("clear", &std::vector<uchar>::clear)
    .def("pop_back", &std::vector<uchar>::pop_back)
    .def("__len__", [](const std::vector<uchar> &v) { return v.size(); })
    .def("__iter__", [](std::vector<uchar> &v) {
       return py::make_iterator(v.begin(), v.end());
    }, py::keep_alive<0, 1>()); /* Keep vector alive while iterator is used */

    py::class_<ApplicationInterface>(m, "Application")
        .def(py::init<>())
        .def("get", &ApplicationInterface::get)
        .def("getImage",&ApplicationInterface::getImage)
        .def_readwrite("image", &ApplicationInterface::m_arr);
}

int main(int argc, char** argv)
{
    //starting python intepreter. this should done once per process. Ideally better in main function
    py::scoped_interpreter guard{};

    auto app = App::getApplication();
    cv::Mat image = cv::imread("R.png");
    app->setImage(image);
    py::object scope = py::module_::import("__main__").attr("__dict__");

    // loading test.py as module
    py::module_ calc = py::module_::import("test");

    calc.attr("test_func")(1);

    return 0;
}