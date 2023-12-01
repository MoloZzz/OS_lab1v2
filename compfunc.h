//
// Created by megao on 01.12.2023.
//

#ifndef OS_LAB1_V2_COMPFUNC_H
#define OS_LAB1_V2_COMPFUNC_H


#include <variant>
#include <iostream>

namespace os::lab1::compfunc {

    struct hard_fault {};
    struct soft_fault {};

    template<typename T>
    using comp_result = std::variant<hard_fault, soft_fault, T>;

    enum op_group { BITWISE_XOR, DOUBLE_SUM, GCD, DOUBLE_MAX, CONCAT }; //AND, OR,

    template<typename T>
    struct op_group_type_traits {
        typedef T value_type;
        typedef comp_result<T> result_type;
    };

    static
    std::ostream& operator<<(std::ostream& os, const hard_fault) {
        os << "critical fault";
        return os;
    }

    static
    std::ostream& operator<<(std::ostream& os, const soft_fault) {
        os << "non-critial fault";
        return os;
    }

    template<typename T>
    std::ostream& operator<<(std::ostream& os, const comp_result<T> &res) {
        switch (res.index()) {
            case 0:
                return os << hard_fault();
            case 1:
                return os << soft_fault();
            case 2:
                return os << "val(" << std::get<2>(res) << ")";
        }
        return os;
    }

    template<op_group O>
    struct op_group_traits;

    template<>
    struct op_group_traits<BITWISE_XOR> : op_group_type_traits<unsigned> {};

    template<>
    struct op_group_traits<GCD> : op_group_type_traits<int> {};

    template<>
    struct op_group_traits<DOUBLE_SUM> : op_group_type_traits<double> {};

    template<>
    struct op_group_traits<DOUBLE_MAX> : op_group_type_traits<double> {};

    template<>
    struct op_group_traits<CONCAT> : op_group_type_traits<std::string> {};

}

#endif //OS_LAB1_V2_COMPFUNC_H
