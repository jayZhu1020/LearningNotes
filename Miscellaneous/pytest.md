# Pytest

## Basics
If we call 
```console
$ pytest <path>
```
then pytest will
1. Recursively look for files under `path`, if no `path` is provided, will recursively look for files from the current directory where the command is called
2. Search for `test_*.py` or `*_test.py`
3. In those files, find
    * `test_func_name` functions outside of class 
    * `test_func_name(self)` functionos inside `TestClassName` (without an __init__ method)

## Invoke pytest
1. Run test in a module
```console
$ pytest test_mod.py
```
2. Run test in a directory
```console
$ pytest testing/
```
3. Run test by node ids
```console
$ pytest test_mod py::test_func
```
4. Run test by mark
```console
$ pytest -m targets
```
This command will run all test functions with fixture `@pytest.mark.targets`
5. Equivalent 
```console
$ python -m pytest <args>
```
6. Calling pytest in python code
```python
retcode = pytest.main()
```
7. Calling pytest in python code with command lin parameters
```python
retcode = pytest.main(["-x", "mytestdir"])
```

## Write and report assertions in tests
Pytest allows you to use the standard Python `assert` for verifying expectations and values in Python tests.
```python
def f():
    return 3

def test_function():
    assert f() == 3
```
When the assertion fails, a trace back is shown. Instead of showing the traceback, a custom message can instead be shown:
```python
assert f() == 3, "The value is not 3"
```



