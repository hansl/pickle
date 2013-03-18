
----

Parameterizable Configuration Language
=======

# PCL
This is the repository for Pickle, a declarative language to simplify configurations of software that are distributed in different.

# Usage
Please check the API.md for a complete description of the API and classes.

----

# Sample

## Simple Example

----

    # main.pcl
    @function language(): @string;

    is_french = language() == 'fr';
    is_spanish = language() == 'es';

    MyNamespace = {
      param = "Hello";
      param2 =             param + " World"
             | is_french:  param + " Monde"
             | is_spanish: param + " Mundo";
    }
    MyOtherNamespace = {
      another_param = MyNamespace.param;
    }

----

    // main.cc
    // #include <...>
    #include <pcl.h>

    std::string language;  // Just for testing purpose.
    std::string language() {
      return language;
    }

    int main() {
      std::function<language> f;
      pcl::parser p;

      p.register("language", f);
      p.read(std::ifstream("main.pcl"));

      language = "en";
      assert(p.query("MyNamespace.param2") == "Hello World");
      language = "fr";
      assert(p.query("MyNamespace.param2") == "Hello Monde");

      return 0;
    }

----

## Experimentation

----

    # experiment.pcl
    @experiment my_experiment;

    @if my_experiment() {
      @int param1 = 123;
    }
    @else {
      @int param2 = 456;
    }

----

    # main.cc
    #include <pcl.h>

    int main() {
      pcl::parser p;
      // Parameter could also be a std::function<bool()>.
      p.set_experiment("my_experiment");

      p.read(std::ifstream("main.pcl"));
      assert(p.query("param1") == 123);
      assert(p.query("param2"));  // will throw a pcl::NonExistentParam("param2").
    }
