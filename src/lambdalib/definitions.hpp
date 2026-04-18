#pragma once

#include "nodes.hpp"

namespace llib {

namespace def {

namespace val {

// BOOLEAN VALUES

inline const std::unique_ptr<LambdaBase> TRUE =  //
  std::make_unique<Function>(                    //
    Variable('x'),                               //
    std::make_unique<Function>(                  //
      Variable('y'),                             //
      std::make_unique<Variable>('x')            //
      )                                          //
  );                                             //

inline const std::unique_ptr<LambdaBase> FALSE =  //
  std::make_unique<Function>(                     //
    Variable('x'),                                //
    std::make_unique<Function>(                   //
      Variable('y'),                              //
      std::make_unique<Variable>('y')             //
      )                                           //
  );                                              //

// BOOLEAN OPERATIONS

inline const std::unique_ptr<LambdaBase> NOT =  //
  std::make_unique<Function>(                   //
    Variable('p'),                              //
    std::make_unique<Application>(              //
      std::make_unique<Application>(            //
        std::make_unique<Variable>('p'),        //
        FALSE->copy()                           //
        ),                                      //
      TRUE->copy()                              //
      )                                         //
  );                                            //

inline const std::unique_ptr<LambdaBase> AND =  //
  std::make_unique<Function>(                   //
    Variable('p'),                              //
    std::make_unique<Function>(                 //
      Variable('q'),                            //
      std::make_unique<Application>(            //
        std::make_unique<Application>(          //
          std::make_unique<Variable>('p'),      //
          std::make_unique<Variable>('q')       //
          ),                                    //
        std::make_unique<Variable>('p')         //
        )                                       //
      )                                         //
  );                                            //

inline const std::unique_ptr<LambdaBase> OR =  //
  std::make_unique<Function>(                  //
    Variable('p'),                             //
    std::make_unique<Function>(                //
      Variable('q'),                           //
      std::make_unique<Application>(           //
        std::make_unique<Application>(         //
          std::make_unique<Variable>('p'),     //
          std::make_unique<Variable>('p')      //
          ),                                   //
        std::make_unique<Variable>('q')        //
        )                                      //
      )                                        //
  );                                           //

inline const std::unique_ptr<LambdaBase> IFTHENELSE =  //
  std::make_unique<Function>(                          //
    Variable('p'),                                     //
    std::make_unique<Function>(                        //
      Variable('a'),                                   //
      std::make_unique<Function>(                      //
        Variable('b'),                                 //
        std::make_unique<Application>(                 //
          std::make_unique<Application>(               //
            std::make_unique<Variable>('p'),           //
            std::make_unique<Variable>('a')            //
            ),                                         //
          std::make_unique<Variable>('b')              //
          )                                            //
        )                                              //
      )                                                //
  );                                                   //

}  // namespace val

// SHORTHANDS

inline std::unique_ptr<LambdaBase> TRUE() { return val::TRUE->copy(); }

inline std::unique_ptr<LambdaBase> FALSE() { return val::FALSE->copy(); }

inline std::unique_ptr<LambdaBase> NOT() { return val::NOT->copy(); }

inline std::unique_ptr<LambdaBase> AND() { return val::AND->copy(); }

inline std::unique_ptr<LambdaBase> OR() { return val::OR->copy(); }

inline std::unique_ptr<LambdaBase> IFTHENELSE() {
  return val::IFTHENELSE->copy();
}

}  // namespace def

}  // namespace llib