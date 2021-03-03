# -*- coding: utf-8 -*-

"""
Package leadd
=======================================

Top-level package for leadd.
"""

__version__ = "0.0.0"

try:
    import leadd.core
except ModuleNotFoundError as e:
    # Try to build this binary extension:
    from pathlib import Path
    import click
    from et_micc_build.cli_micc_build import auto_build_binary_extension
    msg = auto_build_binary_extension(Path(__file__).parent, 'core')
    if not msg:
        import leadd.core
    else:
        click.secho(msg, fg='bright_red')


def hello(who='world'):
    """'Hello world' method.

    :param str who: whom to say hello to
    :returns: a string
    """
    result = "Hello " + who
    return result

# Your code here...