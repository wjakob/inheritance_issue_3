from setuptools import Extension, setup

setup(
    ext_modules=[
        Extension(
            name="inheritance_issue_3",
            sources=["inheritance_issue_3.c"],
        ),
    ]
)
