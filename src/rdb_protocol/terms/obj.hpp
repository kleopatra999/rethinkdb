#ifndef RDB_PROTOCOL_TERMS_OBJ_HPP_
#define RDB_PROTOCOL_TERMS_OBJ_HPP_

#include "rdb_protocol/op.hpp"
#include "rdb_protocol/err.hpp"

namespace ql {

class getattr_term_t : public op_term_t {
public:
    getattr_term_t(env_t *env, const Term *term)
        : op_term_t(env, term, argspec_t(2)) { }
private:
    virtual val_t *eval_impl() {
        return new_val(arg(0)->as_datum()->el(arg(1)->as_str()));
    }
    RDB_NAME("getattr");
};

class contains_term_t : public op_term_t {
public:
    contains_term_t(env_t *env, const Term *term)
        : op_term_t(env, term, argspec_t(1, -1)) { }
private:
    virtual val_t *eval_impl() {
        const datum_t *obj = arg(0)->as_datum();
        bool contains = true;
        for (size_t i = 1; i < num_args(); ++i) {
            contains = contains && obj->el(arg(i)->as_str(), NOTHROW);
        }
        return new_val(new datum_t(datum_t::R_BOOL, contains));
    }
    RDB_NAME("contains");
};

} // namespace ql

#endif // RDB_PROTOCOL_TERMS_OBJ_HPP_