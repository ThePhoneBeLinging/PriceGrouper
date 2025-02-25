# Parameters:

### PercentageGapInGroups

Percentage that is used to calculate the min/max value that determines
which elements belong in a SmallGroup together.
E.G Which prices fall into the same "container".
If for example the first price of a day is:
1000, a value of 5 will allow all prices in the interval:

951 -> 1050. With 951 being included, but 1050 not being included.


### MinimumGapInGroupsCents

If this parameter yields a larger allowed interval than the
result of PercentageGapInGroups, this value is used instead.

For example, lets say the first price is 1000,
and it is set to 5%. Any value above 50 will then cause this parameter
to be used instead.
A value of 100 would for example yield the interval:

901 -> 1100, with 901 being included, but 1100 not.

### MaximumGapInGroupsCents

All grouping of prices, will have at least 2 elements, unless
the difference between the prices is more than this value.
For example if this value is 50, and the following prices are found

100, 140, 149.
Then the first 2 will be in a group no matter what. And the 3rd element
will not be included no matter what.

100, 151, 120.
In this example 100 will be in a group for itself,
as the max difference is exceeded.

But if it was
100, 150, 120

Then they would all 3 be in the same group.

