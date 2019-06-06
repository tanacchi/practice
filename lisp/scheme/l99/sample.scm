(define pack-aux
  (lambda (xs tmp ret)
    (display ret)
    (newline)
    (cond
      ((null? xs) (cons tmp ret))
      ((null? tmp) (pack-aux (cdr xs) (list (car xs)) ret))
      ((eq? (car xs) (car tmp))
       (pack-aux (cdr xs) (cons (car xs) tmp) ret))
      (else
       (pack-aux (cdr xs) (list (car xs)) (cons tmp ret))))))

(define pack
  (lambda (xs)
    (reverse (pack-aux xs '() '()))))

(display (pack '(0 0 0 0 1 1 2 2 2 3 3 3 3 4 5 5)))
