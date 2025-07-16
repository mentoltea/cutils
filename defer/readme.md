# Defer
## Usage
Include the header file [`defer.h`](./defer.h).  
The function you want to be defering in should look like
```C
T func(...) {
DEFERABLE( * All variables used in defer* )
DEFER( *Defer body* )
BODY( *Function body* )
}
```
Inside the function body instead of `return` use `dreturn` - but keep in mind that you cannot pass resulting value through it. If function needs to return something, use variables from `DEFERABLE` section.  
If function does not return anything and doesn't use variables inside `DEFER`, than you can leave it empty: `DEFERABLE()`.  
You can see [concrete example](./example.c).  
`DEFERABLE` should always be defined at the top of the function, but position of `DEFER` and `BODY` is not relevant.  
You can place code between the blocks, but it is HIGHLY unrecommended.

## Authors
*Agoev T* - [github](https://github.com/mentoltea) | [telegram](https://web.telegram.org/k/#@lacus_lacrimalis) : @lacus_lacrimalis