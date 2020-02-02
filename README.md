# varstr 1.4.0-dev0.

C-scrap class providing a variable length string. Useful for building up a
string.

## From the prototypes:

```c
    /* Create and return a new varstr object */
    struct varstr *varstr_new(void);
    /* Clean up and free a varstr structure */
    int         varstr_free(struct varstr **pp);
    /* Return the version of this package */
    const char *varstr_version(void);

    /* Sets parameters for the internal buffer */
    int         varstr_buffersize(struct varstr *p, unsigned size, unsigned extend);
    /* Concatenate a string to the end of a varstr object */
    void        varstr_cat(struct varstr *p, char *x);
    /* Concatenate a character to the end of a varstr object */
    void        varstr_catc(struct varstr *p, char x);
    /* Remove whitespace from the end of a varstr object */
    void        varstr_chomp(struct varstr *p);
    /* Remove all whitespace from a varstr */
    void        varstr_compact(struct varstr *p);
    /* Reset to the empty varstr */
    void        varstr_empty(struct varstr *p);
    /* Set the extension size for a varstr object */
    unsigned    varstr_extend(struct varstr *p, unsigned extend);
    /* Initialize a varstr object */
    unsigned    varstr_init(struct varstr *p, unsigned extend);
    /* Remove whitespace from both ends */
    void        varstr_lrtrim(struct varstr *g);
    /* Get the pointer to the internal buffer holding the string */
    char       *varstr_str(struct varstr *p);
    /* Get the string represented by the varstr */
    char       *varstr_to_s(struct varstr *p);
```

For the call `varstr\_cat(p, x)`, `x` must not overlap with the internal buffer of
`p`. For example `varstr\_cat(p, varstr\_str(p))` could yield unexpected results. If
you really need to do something like that, use `varstr\_cat(p, varstr\_to\_s(p)`.
