#!/bin/bash
function build_dependency(){
    DEPENDENCY_NAME=$2
    echo "Building dependency: $DEPENDENCY_NAME"
    if [[ "$*1" == *"-d"*  ]]
    then
      BUILD_TYPE="Debug"
      FOLDER="cmake-build-debug"
    else
      BUILD_TYPE="Release"
      FOLDER="cmake-build-release"
    fi

    TESTS="-DDISABLE_TESTING=YES"

    if [[ "$*1" == *"-t"*  ]]
    then
      TESTS=""
    fi

    cd "$DEPENDENCY_NAME"

    #recursevily builds all dependencies
    if test -f "dependencies/build_all.sf"; then
        cd dependencies
        build_all.sf
        cd ..
    fi

    if [ -f "CMakeLists.txt" ]
    then
      if [ -d "./cmake-build-release" ]
      then
        if [[ "$*1" == *"-c"*  ]]
        then
          rm $FOLDER -r
        fi
      fi
      mkdir $FOLDER -p


      cd $FOLDER
      CXX=g++-10 CC=gcc-10 cmake .. -DCMAKE_BUILD_TYPE=$BUILDTYPE $TESTS

      if [[ "$*1" == *"-i"*  ]]
      then
        make -j install
      else
        make -j
      fi
    else
      echo "No cmake project file (CMakeLists.txt) found at $DEPENDENCY_NAME"
    fi
}

function update_dependency(){
  echo "repository $1"
  echo "folder $2"
  if [ -d "$2" ];
  then
    cd $2
    git pull
  else
    git clone $1 $2
  fi
}

#git submodule update --init --recursive
#
#
#for f in *; do
#    if [ -d "$f" ]; then
#        dependencies+=("$f")
#    fi
#done
#ROOT_FOLDER=$(pwd)
#
#for dependency in "${dependencies[@]}"
#do
#  cd "$ROOT_FOLDER"
#  build_dependency $dependency $@
#done

dependencies=()
while IFS= read -r line
do
  update_dependency $line
  build_dependency $line $@
done < "dependencies.config"

#for dependency in "${dependencies[@]}"
#do
#  cd "$ROOT_FOLDER"
#  update_dependency $dependency
#  build_dependency $dependency $@
#done