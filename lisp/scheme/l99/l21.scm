(define (insert-at new lst pos)
  (define (insert-at-aux new lst pos buff)
    (cond
      ((null? lst) '())
      ((eq? pos 1) (append (reverse buff) (cons new (cdr lst))))
      (else (insert-at-aux new (cdr lst) (- pos 1) (cons (car lst) buff)))))
  (insert-at-aux new lst pos '()))

(print (insert-at 'a '(0 1 2 3 4 5) 3))
