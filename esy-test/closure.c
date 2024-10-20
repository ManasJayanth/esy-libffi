// From https://github.com/Homebrew/homebrew-core/blob/5eb3a4076a7106d068b88bd8ea6b7493590c724f/Formula/lib/libffi.rb#L41-L85
// Same license applies to this file
#include <stdio.h>
#include <ffi.h>

/* Acts like puts with the file given at time of enclosure. */
void puts_binding(ffi_cif *cif, void *ret, void** args, void *stream)
{
  *(unsigned int *)ret = fputs(*(char **)args[0], (FILE *)stream);
}

int main()
{
  ffi_cif cif;
  ffi_type *args[1];
  ffi_closure *closure;

  int (*bound_puts)(char *);
  int rc;

  /* Allocate closure and bound_puts */
  closure = ffi_closure_alloc(sizeof(ffi_closure), &bound_puts);

  if (closure)
    {
      /* Initialize the argument info vectors */
      args[0] = &ffi_type_pointer;

      /* Initialize the cif */
      if (ffi_prep_cif(&cif, FFI_DEFAULT_ABI, 1,
                       &ffi_type_uint, args) == FFI_OK)
        {
          /* Initialize the closure, setting stream to stdout */
          if (ffi_prep_closure_loc(closure, &cif, puts_binding,
                                   stdout, bound_puts) == FFI_OK)
            {
              rc = bound_puts("Hello World!");
              /* rc now holds the result of the call to fputs */
            }
        }
    }

  /* Deallocate both closure, and bound_puts */
  ffi_closure_free(closure);

  return 0;
}
