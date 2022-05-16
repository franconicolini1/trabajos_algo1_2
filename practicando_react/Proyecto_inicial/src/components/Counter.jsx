import React, {Fragment, useState} from 'react';

const Counter = () => {
    const [number, setNumber] = useState(0);

    const aumentar = () => {
        setNumber(number + 1);
    }

    const reducir = () => {
        setNumber(number - 1);
    }

    return(
        <Fragment>
            <h2>Cantidad del Contador: {number}</h2>
            <button onClick={aumentar}>Aumentar</button>
            <button onClick={reducir}>Reducir</button>
        </Fragment>
    )
}

export default Counter;