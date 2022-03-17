
#include "idaklu_python.hpp" 
#include "idaklu.hpp" 
#include "idaklu_casadi.hpp" 

#include <pybind11/pybind11.h>
#include <pybind11/stl_bind.h>
#include <pybind11/functional.h>

PYBIND11_MAKE_OPAQUE(std::vector<np_array>);

PYBIND11_MODULE(idaklu, m)
{
  m.doc() = "sundials solvers"; // optional module docstring

  py::bind_vector<std::vector<np_array>>(m, "VectorNdArray");

  m.def("solve_python", &solve_python, "The solve function for python evaluators", 
        py::arg("t"), py::arg("y0"),
        py::arg("yp0"), py::arg("res"), py::arg("jac"), py::arg("sens"), 
        py::arg("get_jac_data"),
        py::arg("get_jac_row_vals"), py::arg("get_jac_col_ptr"), py::arg("nnz"),
        py::arg("events"), py::arg("number_of_events"), py::arg("use_jacobian"),
        py::arg("rhs_alg_id"), py::arg("atol"), py::arg("rtol"),
        py::arg("number_of_sensitivity_parameters"),
        py::return_value_policy::take_ownership);

  m.def("solve_casadi", &solve_casadi, "The solve function for casadi evaluators", 
        py::arg("t"), py::arg("y0"), py::arg("yp0"), 
        py::arg("rhs_alg"), 
        py::arg("jac_times_cjmass"), 
        py::arg("jac_times_cjmass_rowvals"), 
        py::arg("jac_times_cjmass_colptrs"), 
        py::arg("jac_times_cjmass_nnz"), 
        py::arg("jac_action"), 
        py::arg("jacp_action"), 
        py::arg("mass_action"), 
        py::arg("sens"), 
        py::arg("events"), py::arg("number_of_events"), 
        py::arg("use_jacobian"),
        py::arg("rhs_alg_id"),
        py::arg("atol"), py::arg("rtol"),
        py::arg("number_of_sensitivity_parameters"),
        py::return_value_policy::take_ownership);


  py::class_<Solution>(m, "solution")
      .def_readwrite("t", &Solution::t)
      .def_readwrite("y", &Solution::y)
      .def_readwrite("yS", &Solution::yS)
      .def_readwrite("flag", &Solution::flag);
}

