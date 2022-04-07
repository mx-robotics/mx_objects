# mx_objects


## Install
### Simple
```shell
git clone https://github.com/mx-robotics/mx_objects.git
cd mx_objects
mkdir build
cd build
cmake ..
make 
sudo make install
```
### Installation into a spezific folder
```shell
# devine installation forder
export MXObjects_INSTALL_PREFIX=/opt/mxr
git clone https://github.com/mx-robotics/mx_objects.git
cd mx_objects
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=$MXObjects_INSTALL_PREFIX .. 
# extend the ld search path
sudo sh -c "echo $MXObjects_INSTALL_PREFIX/lib > /etc/ld.so.conf.d/mx_objects.conf"
sudo ldconfig
# make cmake config avaliable
echo "export MXObjects_DIR=$MXObjects_INSTALL_PREFIX/lib/CMake" >> ~/.bashrc
make 
sudo make install
```
### Test

```shell
 ./common/examples/mx_demo_joystick /dev/input/js0 # for testing

```
## Uninstall
Be careful on this!
```shell
sudo make uninstall
```

## Usage with cmake
Add the following statements to your CMakeLists.txt
```
...
find_package(MXObjects REQUIRED)
include_directories(${MXObjects_INCLUDE_DIRS})
...
target_link_libraries(your_target ${MXObjects_LIBRARIES})
...

```
