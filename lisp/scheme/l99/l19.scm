(define rotate-aux
  (lambda (lst pos buff)
    (cond
      ((null? lst) buff)
      ((zero? pos) (append lst (reverse buff)))
      (else (rotate-aux (cdr lst) (- pos 1) (cons (car lst) buff ))))))

(define rotate
  (lambda (lst pos)
    (rotate-aux lst pos '())))


(display (rotate '(0 1 2 3 4 5 6) 3))
