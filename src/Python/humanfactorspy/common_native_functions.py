from ctypes import *
from humanfactorspy.Exceptions import *
from typing import *
import os
import numbers

# This is used to check if an object is a number

# This is the name of the humanfactors DLL
dllname = "HumanFactors.dll"

HFPython: Union[None, CDLL] = None  # The C++ DLL containing all functionality we need


# Try to load the DLL, and throw if it fails


def getDLLHandle() -> CDLL:
    """ Get a reference to the C++ DLL """
    global HFPython
    if HFPython is not None: return HFPython
    try:
        directory = os.path.dirname(os.path.realpath(__file__)) + "\\bin"
        os.add_dll_directory(directory)

        HFPython = CDLL(directory + "\\" + dllname, use_last_error=True)
    except FileNotFoundError as e:
        print("CDLL Failed to load!")
        print(e)
        raise e

    return HFPython


def GetStringPtr(string: str) -> c_char_p:
    """ A quick and consistent way to convert strings into c-strings for C++"""
    strptr = c_char_p()
    strptr.value = (string + "\0").encode("utf-8")
    return strptr


def ConvertPointsToArray(
    points: Union[Tuple[float, float, float], Iterable[Tuple[float, float, float]]]
) -> c_float:
    """ Convert a list of floats to a flat c-style array """
    # If it's a tuple or list of floats, just do the one
    if (
            isinstance(points, (tuple))
        ) or (  # IF this is a list, we need a little more proof
                # that this shouldn't go in the else clause
            isinstance(points, list)  # Must be a list
            and isinstance(points[0], numbers.Number)  # Must hold numbers
            and len(points) == 3  # Must be a length of 3
        ):
        point_arr_type = c_float * 3
        point_arr = point_arr_type()
        point_arr[0] = points[0]
        point_arr[1] = points[1]
        point_arr[2] = points[2]
    else:
        point_arr_type = c_float * (len(points) * 3)
        point_arr = point_arr_type()
        for i in range(0, len(points) * 3):
            point_arr[i] = points[int(i / 3)][i % 3]

    return point_arr


def ConvertFloatsToArray(floats: Iterable[float]) -> c_float:
    float_type = c_float * len(floats)
    float_arr = float_type()
    for i in range(0, len(floats)):
        float_arr[i] = floats[i]

    return float_arr


def ConvertIntsToArray(ints: Iterable[int]) -> c_int:
    int_type = c_int * len(ints)
    int_arr = int_type()
    for i in range(0, len(ints)):
        int_arr[i] = ints[i]

    return int_arr
