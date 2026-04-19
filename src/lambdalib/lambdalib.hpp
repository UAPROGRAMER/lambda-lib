#pragma once

#include <memory>
#include <string>

#define LAMBDALIB_VERSION (1)

#include "nodes.hpp"

#ifndef LAMBDALIB_NOPRINT
#include "print_visitor.hpp"
#endif

#ifndef LAMBDALIB_NOREDUCE
#include "reduce_visitor.hpp"
#endif

#ifndef LAMBDALIB_NODEFINITIONS
#include "definitions.hpp"
#endif

#ifndef LAMBDALIB_NOPARSER
#include "parser.hpp"
#endif