; make list of the first elements

(define firsts
  (lambda (lst)
    (cond
      ((null? lst) '())
      (else (cons (caar lst) (firsts (cdr lst)))))))

(print (firsts '((0 1 2) (3 4 5) (6 7 8) (9))))
