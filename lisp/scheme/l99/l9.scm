(define (pack-aux lst buff r-result)
  (cond
    ((null? lst) (cons buff r-result))
    ((null? buff) (pack-aux (cdr lst) (list (car lst)) r-result))
    ((eq? (car lst) (car buff)) (pack-aux (cdr lst) (cons (car lst) buff) r-result))
    (else (pack-aux (cdr lst) (list (car lst)) (cons buff r-result)))))

(define (pack lst)
  (reverse (pack-aux lst '() '())))


(display (pack '(0 0 0 1 1 2 3 3 3 4 5 5)))
