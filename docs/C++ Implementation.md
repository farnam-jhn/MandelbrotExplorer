In [The math behind](obsidian://open?vault=Mandelbrot%20Exploler&file=The%20math%20behind) we saw we need to check if a recursive function converges as its arguments moves to infinity 
however we don't have infinity in Computer world
as we don't have infinite resources

### Approach
since we have limited resources, there is a common approach to check if a complex constant like `c` is in the set or not:
we can use a loop that calculates `Z(n+1)` from `Z(n)` 
then we can check two things :
1. is `Z` getting bigger and bigger 
2. how many times we irritated the loop

#### Why number one matters :

to check the first thing we can choose a number as our bounding magnitude.
this is useful because `Z` starts from `(0,0)` and if it grows more than a curtain magnitude (breaks a limited bound) then it definitely gets unbounded and it can never shrink and get lower than that magnitude.
this is because when `|Z| >= magnitude` we have : `|Z|^2 >= magnitude * |Z|`.

#### Why number two matters :

irritations count matters because if a curtain `C` gives us divergence the computer would never know this.
this means the divergence checker function actually reaches a `C` that makes the `Z(n+1) = (Z(n))^2 + c` sequence divergence it just calculates more and more `Z`s. since we can't reach infinity (where we can make sure C makes the sequence divergent) we can limit the loop so after a curtain amount of irritations it supposes C makes the sequence divergent. 
#### Simple optimization 

instead of comparing the actual magnitude to a number we can compare norm of the `Z` to square of the magnitude:
```Math
Z = a + bi
|Z| = sqrt(a^2 + b^2)
norm(Z) = Z.conj(Z) = |Z|^2 = a^2 + b^2
```
using this approach we skipped a square root. this would make the calculations faster



