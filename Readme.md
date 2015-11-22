# Install

`sudo apt-get install gcc python-pip`

`sudo pip install when-changed`


# Run/Watch

exec first make task, here: make compile:
`make`

comile and run:
`make default app=bucketsort_test`

auto re-compile and re-run on file change:
`make watch app=bucketsort_test`

`app=` has its default value set to bucketsort_test, therefore you could easily skip this parameter.
